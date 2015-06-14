bypay extension
====

# 简介
bypay.so扩展主要为解决同一套PHP项目代码部署在不同服务器上时的不同部署环境核心配置读取问题，确保相关核心配置不出现php代码中，并且集中统一管理，确认不同机房服务器不同环境（测试，debug，线上）PHP代码核心配置读写逻辑一致。

# 环境要求
PHP5.2以上
linux下gcc编译安装

# 安装
1 解压源码 unzip bypay.zip<br/>
2 在bypay源码根目录下，执行 /usr/local/php/bin/php/phpize<br/>
3 ./configure<br/>
4 make && make install<br/>
5 编译完成so文件后，会在php的so扩展目录生成so文件：Installing shared extensions: /usr/local/php/lib/php/extensions/no-debug-non-zts-20100525/,:!:可能不同php版本的扩展目录不是在*/no-debug-non-zts-20100525下时，请移动bypay.so到PHP版本对应扩展目录下;
php.ini增加bypay.so的配置:<br/>
```c
;前面省略
[bypay]
extension = bypay.so
;项目配置文件路径,如果未指定，则默认为“/usr/local/php/etc/default.ini”
bypay.cfg_path=/usr/local/php/etc/bypay.ini 
```

default.ini项目配置文件：<br/>
```c
;project config
BYPAY.secret=123123123123
 
;mysql config
MYSQL.db_name=xxxx
MYSQL.db_usr=xxx
MYSQL.db_pwd=xxxx
MYSQL.db_host=localhost
MYSQL.db_port=3388
 
;redis config
REDIS.ports=45001,45002,45003,45004
 
MEMCACHE.port=10009
```

# 函数调用

##bypay_version

###Description
```php
string bypay_version()
```
####获取扩展当前版本号

###Parameters

无

###Return Values

string 当前版本号

###Example
```php
echo bypay_version();
```

##bypay_cfg_get

###Description
```php
string function bypay_cfg_get(string $cfg_key, [string $default_value])
```
获取$section分区下的key为$cfg_key的配置值<br/>

###Parameters

$cfg_key string ini配置文件分区下的配置key<br/>

$default_value string (可选)当配置key查找不到时的默认值<br/>

###Return Values

string 配置值<br/>

###Example
```php
<?php
    //获取MYSQL数据访问配置
    //为了便于区分不同类型配置（例如mysql，cache，队列等类型），
    //建议以"配置类型.配置项"命名key
    $db_name=bypay_cfg_get('MYSQL.db_name');
    $db_usr=bypay_cfg_get('MYSQL.db_usr');
    $db_pwd=bypay_cfg_get('MYSQL.db_pwd');
    $db_host=bypay_cfg_get('MYSQL.db_host');
    $db_port=bypay_cfg_get('MYSQL.db_port');
    echo "{$db_name},{$db_usr},{$db_pwd},{$db_host},{$db_port}\n\n";
 
    //获取redis端口列表，以逗号分隔字符串
    $redis_ports_str=bypay_cfg_get('REDIS.ports');
    $redis_ports = explode(',',$redis_ports_str);
    echo "{$redis_ports_str} \n\n";
    var_dump( $redis_ports );
 
    //memcache端口配置	
    $mc_port=bypay_cfg_get('memcache.port');
    echo $mc_port."\n\n";
    //默认值的调用例子	
    $mxx_port=bypay_cfg_get('mxx.port', '默认值');
    echo $mxx_port."\n\n";    
```



