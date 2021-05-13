# VOCPABE(版本2021.1.1)
 可验证外包加解密实验仿真系统——VOCPABE(verifiable outsourcing cipher-policy attribute based encryption)
 
软件开发平台:win7+vs2019+qt6.1.0(msvc32bit编译器)

 系统中有五个软件（32bit）：KDS(keyDistributionServer)、DS(DecryptionServer)、ES(EncryptionServer)、SS(StorageServer)、EDClient(EncryptionDecryptionClient)。
 
 KDS：
 1、负责处理用户注册、登录、登出、访问策略登记、请求解密参数等请求。
 2、可信第三方，由KDS管理员管理。
 3、负责在系统初始化时指定属性全集U。
 4、初始化时创建kds数据库和五个数据表。

ES:
1、负责根据加密方上传的外包幂盲化加密参数进行相应幂计算，将多个计算结果返回给加密方并由加密方检验计算结果的正确性，计算无误后生成密文的所有(C,D)对。

DS:
1、负责根据解密方上传的转换密文TCT、系统参数PK、解密方转换密钥TK等参数进行外包解密计算，返回一个计算结果给解密方，解密方验证DS外包解密的正确性，验证无误后计算生成最终明文。

SS:
1、负责储存加密方生成的密文。
2、负责为解密方提供密文下载服务。

EDClient:
1、系统合法用户需要注册并登录使用。
2、用户可在一个客户端进行加密、解密操作。


