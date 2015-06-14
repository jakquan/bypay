# bypay
A php extension for bypay config manage and getter

简介

bypay.so扩展主要为解决同一套PHP项目代码部署在不同服务器上时的不同部署环境核心配置读取问题，确保相关核心配置不出现php代码中，并且集中统一管理，确认不同机房服务器不同环境（测试，debug，线上）PHP代码核心配置读写逻辑一致。


环境要求


安装

解压源码 unzip bypay.zip
在bypay源码根目录下，执行 /usr/local/php/bin/php/phpize
./configure
make && make install
编译完成so文件后，会在php的so扩展目录生成so文件：Installing shared extensions: /usr/local/php/lib/php/extensions/no-debug-non-zts-20100525/,:!:可能不同php版本的扩展目录不是在*/no-debug-non-zts-20100525下时，请移动bypay.so到PHP版本对应扩展目录下;
php.ini增加bypay.so的配置:
