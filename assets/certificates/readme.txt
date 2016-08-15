1. openssl official site: https://www.openssl.org/
2. Where can We get a compiled version of OpenSSL: https://www.openssl.org/community/binaries.html
3. Useful links:
	http://citforum.ru/security/cryptography/openssl/
	http://habrahabr.ru/post/192446/

	#################################################################
	# This manual describes how to generate Self-signed certificate #
	#################################################################

1. To generate an RSA key, use the genrsa command (Private key):
	1.1 with passphrase:
		openssl genrsa -aes128 -out fd.key 2048
	1.2 without passphrase:
		openssl genrsa -out fd.key 2048

2. Creating Certificate Signing Requests (CSR):
	openssl req -new -key fd.key -out fd.csr
	2.1 How to check that the CSR is correct:
		openssl req -text -in fd.csr -noout

3. Signing Your Own Certificate:
	openssl x509 -req -days 365 -in fd.csr -signkey fd.key -out fd.crt
	3.1 Examining Certificates
		openssl x509 -text -in fd.crt -noout

4. PKCS#12 (PFX) Conversion (If you need):
	openssl pkcs12 -export -name "My Certificate" -out fd.p12 -inkey fd.key -in fd.crt

	#############################################################
	# This manual describes how to create Certificate Authority #
	#############################################################

	#################################################
	1 First of all we need to create root certificate:

1. To generate an RSA key, use the genrsa command (Private key):
	1.1 with passphrase:
		openssl genrsa -aes128 -out root.key 2048
	1.2 without passphrase:
		openssl genrsa -out root.key 2048

2. Creating Certificate Signing Requests (CSR):
	openssl req -new -key root.key -out root.csr
	2.1 How to check that the CSR is correct:
		openssl req -text -in root.csr -noout

3. Signing Your Own Certificate:
	openssl x509 -req -days 365 -in root.csr -signkey root.key -out root.crt
	3.1 Examining Certificates
		openssl x509 -text -in root.crt -noout

	#####################################################
	2 Creating a certificate signed by root's certificate:

1. To generate an RSA key, use the genrsa command (Private key):
	1.1 with passphrase:
		openssl genrsa -aes128 -out server.key 2048
	1.2 without passphrase:
		openssl genrsa -out server.key 2048

NOTE: On this step important to set valid domain or ip address (for example "localhost")
2. Creating Certificate Signing Requests (CSR):
	openssl req -new -key server.key -out server.csr
	2.1 How to check that the CSR is correct:
		openssl req -text -in server.csr -noout

3. Sign server CSR with root сertificate:
	openssl x509 -req -in server.csr -CA root.crt -CAkey root.key -CAcreateserial -out server.crt -days 365

4. PKCS#12 (PFX) Conversion:
	openssl pkcs12 -export -in root.crt -inkey root.key -out root.p12 -name "Root Certificate (c) Definename"

	###########################
	How to use all these stuff:
	1. "root.p12" should be installed into your browser (Chrome -> Settings -> Manage Certificates -> Trusted Root Certificate Authorities -> Import —> root.p12 (There is no password, leave the password's fields blank) -> restart Chrome)
	2. server.crt - server certificate (Use it in your programs).
	3. server.key - server private key (Use it in your programs).

	###############
	# Enjoy it!!! #
	###############