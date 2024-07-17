//============================================================================
// Name        : crypto_handler.h
// Author      : lisr-pcx
// MIT License (c) 2024 lisr-pcx
//
// CRIsp
// (CRIttografia senza pretese)
//============================================================================

#ifndef CRYPTOHANDLER_H
#define CRYPTOHANDLER_H

#include <QString>
#include <QByteArray>
#include "aes256cbc.h"

/**
 * @brief CryptoHandler class is allowing to encrypt/decrypt files
 */
class CryptoHandler
{
public:

    enum { ENCRYPT,
           DECRYPT,
           NUMBER_OF_OPERATIONS // trick to get the size of enum
    };

    CryptoHandler();
    /**
     * @brief Open a file and encrypt its content
     * @param targetFilePath: Path of file to encrypt
     * @param keyFilePath: Path of .PEM file which contains the key
     * @param ivFilePath: Path of binary (.BIN) file which contains initialization vector
     * @return
     */
    static qint8 encrypt_file(QString const targetFilePath,
                              QString const keyFilePath,
                              QString const ivFilePath);
    /**
     * @brief Open a file and decrypt its content
     * @param targetFilePath: Path of file to encrypt
     * @param keyFilePath: Path of .PEM file which contains the key
     * @param ivFilePath: Path of binary (.BIN) file which contains initialization vector
     * @return
     */
    static qint8 decrypt_file(QString const targetFilePath,
                              QString const keyFilePath,
                              QString const ivFilePath);
    /**
     * @brief Read a single private key contained in .PEM file format (base64)
     * @param filepath: full path of input file
     * @return
     */
    static QByteArray read_pem_file(QString const filepath);
    /**
     * @brief Write a single private key into .PEM file format
     * @param filepath: full path of output file
     * @param keyBase64: private key expressed in Base64
     * @return
     */
    static void write_pem_file(QString const filepath, QString& keyBase64);
    /**
     * @brief Read binary file content
     * @param filepath: full path of input file
     * @return
     */
    static QByteArray read_binary_file(QString const filepath);
    /**
     * @brief Write binary file content
     * @param filepath: full path of output file
     * @param data: byte array of the content
     * @return
     */
    static void write_binary_file(QString const filepath, QByteArray& data);
    /**
     * @brief Compose a final key using XOR-logic
     * @param firstKey: key value
     * @param secondKey: key value
     * @return
     */

protected:
    /**
     * @brief Open a file and decrypt its content
     * @param targetFilePath: Path of file to decrypt
     * @param passphrFilePath: Path of .PEM file which contains the passphrase values
     * @param rootpswFilePath: Path of .PEM file which contains the rootpassword values
     * @param mode: ENCRYPT or DECRYPT the target file
     * @return
     */
    static qint8 check_and_run(QString targetFilePath,
                               QString passphrFilePath,
                               QString rootpswFilePath,
                               qint64 mode);

    static QByteArray create_key(QByteArray first_key, QByteArray second_key);
    /**
     * @brief Add padding bytes using scheme: PKCS#7
     *        Please refer to RFC5652
     *        (https://datatracker.ietf.org/doc/html/rfc5652#section-6.3)
     * @param data: byte array to add padding
     * @param blockSize: block length used by cypher
     * @return
     */
    static void apply_PKCS7_padding(QByteArray& data, quint8 blockSize);
    /**
     * @brief Remove padding bytes using scheme: PKCS#7
     *        Please refer to RFC5652
     *        (https://datatracker.ietf.org/doc/html/rfc5652#section-6.3)
     * @param data: byte array with padding
     * @return
     */
    static void remove_PKCS7_padding(QByteArray& data);
};

#endif // CRYPTOHANDLER_H
