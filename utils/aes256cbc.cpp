//============================================================================
// Name        : aes256cbc.h
// Author      : lisr-pcx
// MIT License (c) 2024 lisr-pcx
//
// CRIsp
// (CRIttografia senza pretese)
//
// This class is based on the work of user "kokke" on ""tiny-AES-c":
// https://github.com/kokke/tiny-AES-c
//============================================================================

#include "aes256cbc.h"
#include <QDebug>
#include <QString>

AES256CBC::AES256CBC()
{
    for (unsigned int i=0; i<localKeySize; i++)
    {
        localKey[i] = 0x00;
    }
    for (unsigned int i=0; i<localIVSize; i++)
    {
        localIV[i] = 0x00;
    }
    keyExpansion(localRoundKey, localKey);
    qDebug() << "Loaded default KEY and IV";
}

AES256CBC::AES256CBC(QByteArray key, QByteArray iv)
{
    this->init(key, iv);
}

void AES256CBC::init(QByteArray key, QByteArray iv)
{
    if (key.size() != localKeySize)
    {
        throw "Invalid AES key size";
    }
    if (iv.size() != localIVSize)
    {
        throw "Invalid AES IV size";
    }
    std::memcpy(localKey, key.data(), localKeySize);
    std::memcpy(localIV, iv.data(), localIVSize);
    keyExpansion(localRoundKey, localKey);
    qDebug() << "Loaded custom KEY ["+ QString::number(localKeySize) +"]" << key ;
    qDebug() << "Loaded custom IV ["+ QString::number(localIVSize) +"]" <<  iv;
}

void AES256CBC::encryptData(QByteArray& data)
{
    // Only accept buffer multiply of 16 bytes
    // (user must apply padding when needed)
    if ( (data.size()>=localIVSize) &&
         ((data.size()%localIVSize)==0) )
    {
        encrypt((uint8_t*) data.data(), data.size());
    }
    else
    {
        qDebug() << "Invalid length of data (" << data.size() << ")";
    }
}

void AES256CBC::decryptData(QByteArray& data)
{
    // Only accept buffer multiply of 16 bytes
    // (user must apply padding when needed)
    if ( (data.size()>=localIVSize) &&
        ((data.size()%localIVSize)==0) )
    {
        decrypt((uint8_t*) data.data(), data.size());
    }
    else
    {
        qDebug() << "Invalid length of data (" << data.size() << ")";
    }
}

/*
 * List of class private methods
 */

void AES256CBC::encrypt(uint8_t* buffer, size_t length)
{
    uint8_t* IV = this->localIV;
    for (size_t i=0; i<length; i+=localIVSize)
    {
        xorWithIv(buffer, IV);
        runCipher((state_t*)buffer, this->localRoundKey);
        IV = buffer;
        buffer += localIVSize;
    }
    /* store Iv in ctx for next call */
    memcpy(this->localIV, IV, localIVSize);
}

void AES256CBC::decrypt(uint8_t* buffer, size_t length)
{
    uint8_t storeNextIv[localIVSize];
    for (size_t i=0; i<length; i+=localIVSize)
    {
        memcpy(storeNextIv, buffer, localIVSize);
        runInvCipher((state_t*)buffer, this->localRoundKey);
        xorWithIv(buffer, localIV);
        memcpy(localIV, storeNextIv, localIVSize);
        buffer += localIVSize;
    }
}

void AES256CBC::keyExpansion(uint8_t* RoundKey, uint8_t* Key)
{
    unsigned i, j, k;
    uint8_t tempa[4]; // Used for the column/row operations

    // The first round key is the key itself.
    for (i = 0; i < Nk; ++i)
    {
        RoundKey[(i * 4) + 0] = Key[(i * 4) + 0];
        RoundKey[(i * 4) + 1] = Key[(i * 4) + 1];
        RoundKey[(i * 4) + 2] = Key[(i * 4) + 2];
        RoundKey[(i * 4) + 3] = Key[(i * 4) + 3];
    }

    // All other round keys are found from the previous round keys.
    for (i = Nk; i < Nb * (Nr + 1); ++i)
    {
        {
            k = (i - 1) * 4;
            tempa[0]=RoundKey[k + 0];
            tempa[1]=RoundKey[k + 1];
            tempa[2]=RoundKey[k + 2];
            tempa[3]=RoundKey[k + 3];
        }

        if (i % Nk == 0)
        {
            // This function shifts the 4 bytes in a word to the left once.
            // [a0,a1,a2,a3] becomes [a1,a2,a3,a0]

            // Function RotWord()
            {
                const uint8_t u8tmp = tempa[0];
                tempa[0] = tempa[1];
                tempa[1] = tempa[2];
                tempa[2] = tempa[3];
                tempa[3] = u8tmp;
            }

            // SubWord() is a function that takes a four-byte input word and
            // applies the S-box to each of the four bytes to produce an output word.

            // Function Subword()
            {
                tempa[0] = getSBoxValue(tempa[0]);
                tempa[1] = getSBoxValue(tempa[1]);
                tempa[2] = getSBoxValue(tempa[2]);
                tempa[3] = getSBoxValue(tempa[3]);
            }

            tempa[0] = tempa[0] ^ Rcon[i/Nk];
        }
        if (i % Nk == 4)
        {
            // Function Subword()
            {
                tempa[0] = getSBoxValue(tempa[0]);
                tempa[1] = getSBoxValue(tempa[1]);
                tempa[2] = getSBoxValue(tempa[2]);
                tempa[3] = getSBoxValue(tempa[3]);
            }
        }
        j = i * 4; k=(i - Nk) * 4;
        RoundKey[j + 0] = RoundKey[k + 0] ^ tempa[0];
        RoundKey[j + 1] = RoundKey[k + 1] ^ tempa[1];
        RoundKey[j + 2] = RoundKey[k + 2] ^ tempa[2];
        RoundKey[j + 3] = RoundKey[k + 3] ^ tempa[3];
    }
}

uint8_t AES256CBC::getSBoxValue(uint8_t num)
{
    return sbox[num];
}

uint8_t AES256CBC::getRSBoxValue(uint8_t num)
{
    return rsbox[num];
}

void AES256CBC::xorWithIv(uint8_t* buf, uint8_t* Iv)
{
    uint8_t i;
    // The block in AES is always 128bit no matter the key size
    for (i=0; i<localIVSize; ++i)
    {
        buf[i] ^= Iv[i];
    }
}

void AES256CBC::runCipher(state_t* state, uint8_t* RoundKey)
{
    uint8_t round = 0;

    // Add the First round key to the state before starting the rounds.
    addRoundKey(0, state, RoundKey);

    // There will be Nr rounds.
    // The first Nr-1 rounds are identical.
    // These Nr rounds are executed in the loop below.
    // Last one without MixColumns()
    for (round = 1; ; ++round)
    {
        subBytes(state);
        shiftRows(state);
        if (round == Nr) {
            break;
        }
        mixColumns(state);
        addRoundKey(round, state, RoundKey);
    }
    // Add round key to last round
    addRoundKey(Nr, state, RoundKey);
}

void AES256CBC::runInvCipher(state_t* state, uint8_t* RoundKey)
{
    uint8_t round = 0;

    // Add the First round key to the state before starting the rounds.
    addRoundKey(Nr, state, RoundKey);

    // There will be Nr rounds.
    // The first Nr-1 rounds are identical.
    // These Nr rounds are executed in the loop below.
    // Last one without InvMixColumn()
    for (round = (Nr - 1); ; --round)
    {
        invShiftRows(state);
        invSubBytes(state);
        addRoundKey(round, state, RoundKey);
        if (round == 0) {
            break;
        }
        invMixColumns(state);
    }
}

void AES256CBC::addRoundKey(uint8_t round, state_t* state, uint8_t* RoundKey)
{
    uint8_t i,j;
    for (i = 0; i < 4; ++i)
    {
        for (j = 0; j < 4; ++j)
        {
            (*state)[i][j] ^= RoundKey[(round * Nb * 4) + (i * Nb) + j];
        }
    }
}

void AES256CBC::subBytes(state_t* state)
{
    uint8_t i, j;
    for (i = 0; i < 4; ++i)
    {
        for (j = 0; j < 4; ++j)
        {
            (*state)[j][i] = getSBoxValue((*state)[j][i]);
        }
    }
}

void AES256CBC::invSubBytes(state_t* state)
{
    uint8_t i, j;
    for (i = 0; i < 4; ++i)
    {
        for (j = 0; j < 4; ++j)
        {
            (*state)[j][i] = getRSBoxValue((*state)[j][i]);
        }
    }
}

void AES256CBC::shiftRows(state_t* state)
{
    uint8_t temp;

    // Rotate first row 1 columns to left
    temp           = (*state)[0][1];
    (*state)[0][1] = (*state)[1][1];
    (*state)[1][1] = (*state)[2][1];
    (*state)[2][1] = (*state)[3][1];
    (*state)[3][1] = temp;

    // Rotate second row 2 columns to left
    temp           = (*state)[0][2];
    (*state)[0][2] = (*state)[2][2];
    (*state)[2][2] = temp;

    temp           = (*state)[1][2];
    (*state)[1][2] = (*state)[3][2];
    (*state)[3][2] = temp;

    // Rotate third row 3 columns to left
    temp           = (*state)[0][3];
    (*state)[0][3] = (*state)[3][3];
    (*state)[3][3] = (*state)[2][3];
    (*state)[2][3] = (*state)[1][3];
    (*state)[1][3] = temp;
}

void AES256CBC::invShiftRows(state_t* state)
{
    uint8_t temp;

    // Rotate first row 1 columns to right
    temp = (*state)[3][1];
    (*state)[3][1] = (*state)[2][1];
    (*state)[2][1] = (*state)[1][1];
    (*state)[1][1] = (*state)[0][1];
    (*state)[0][1] = temp;

    // Rotate second row 2 columns to right
    temp = (*state)[0][2];
    (*state)[0][2] = (*state)[2][2];
    (*state)[2][2] = temp;

    temp = (*state)[1][2];
    (*state)[1][2] = (*state)[3][2];
    (*state)[3][2] = temp;

    // Rotate third row 3 columns to right
    temp = (*state)[0][3];
    (*state)[0][3] = (*state)[1][3];
    (*state)[1][3] = (*state)[2][3];
    (*state)[2][3] = (*state)[3][3];
    (*state)[3][3] = temp;
}

void AES256CBC::mixColumns(state_t* state)
{
    uint8_t i;
    uint8_t Tmp, Tm, t;
    for (i = 0; i < 4; ++i)
    {
        t   = (*state)[i][0];
        Tmp = (*state)[i][0] ^ (*state)[i][1] ^ (*state)[i][2] ^ (*state)[i][3] ;
        Tm  = (*state)[i][0] ^ (*state)[i][1] ; Tm = xTime(Tm);  (*state)[i][0] ^= Tm ^ Tmp ;
        Tm  = (*state)[i][1] ^ (*state)[i][2] ; Tm = xTime(Tm);  (*state)[i][1] ^= Tm ^ Tmp ;
        Tm  = (*state)[i][2] ^ (*state)[i][3] ; Tm = xTime(Tm);  (*state)[i][2] ^= Tm ^ Tmp ;
        Tm  = (*state)[i][3] ^ t ;              Tm = xTime(Tm);  (*state)[i][3] ^= Tm ^ Tmp ;
    }
}

void AES256CBC::invMixColumns(state_t* state)
{
    int i;
    uint8_t a, b, c, d;
    for (i = 0; i < 4; ++i)
    {
        a = (*state)[i][0];
        b = (*state)[i][1];
        c = (*state)[i][2];
        d = (*state)[i][3];

        (*state)[i][0] = multiply(a, 0x0e) ^ multiply(b, 0x0b) ^ multiply(c, 0x0d) ^ multiply(d, 0x09);
        (*state)[i][1] = multiply(a, 0x09) ^ multiply(b, 0x0e) ^ multiply(c, 0x0b) ^ multiply(d, 0x0d);
        (*state)[i][2] = multiply(a, 0x0d) ^ multiply(b, 0x09) ^ multiply(c, 0x0e) ^ multiply(d, 0x0b);
        (*state)[i][3] = multiply(a, 0x0b) ^ multiply(b, 0x0d) ^ multiply(c, 0x09) ^ multiply(d, 0x0e);
    }
}

uint8_t AES256CBC::xTime(uint8_t x)
{
    return ((x<<1) ^ (((x>>7) & 1) * 0x1b));
}

uint8_t AES256CBC::multiply(uint8_t x, uint8_t y)
{
    return (((y & 1) * x) ^
            ((y>>1 & 1) * xTime(x)) ^
            ((y>>2 & 1) * xTime(xTime(x))) ^
            ((y>>3 & 1) * xTime(xTime(xTime(x)))) ^
            ((y>>4 & 1) * xTime(xTime(xTime(xTime(x)))))); /* this last call to xTime() can be omitted */
}
