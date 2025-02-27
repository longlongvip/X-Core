#pragma once

enum Error {
	OK = 0, // 没问题
	FAILED, // 失败
	ERR_UNAVAILABLE, // 不支持或不可用
	ERR_UNCONFIGURED, // 所用的对象未正确设置
	ERR_UNAUTHORIZED, // 未授权
	ERR_PARAMETER_RANGE_ERROR, // 参数超过范围
	ERR_OUT_OF_MEMORY, // 内存溢出
	ERR_FILE_NOT_FOUND, // 文件不存在
	ERR_FILE_BAD_DRIVE, // 驱动错误
	ERR_FILE_BAD_PATH, // 文件路径错误
	ERR_FILE_NO_PERMISSION, // 文件权限
	ERR_FILE_ALREADY_IN_USE, // 文件被占用
	ERR_FILE_CANT_OPEN, // 文件无法打开
	ERR_FILE_CANT_WRITE, // 文件无法写入
	ERR_FILE_CANT_READ, // 文件无法读取
	ERR_FILE_UNRECOGNIZED, // (15)
	ERR_FILE_CORRUPT, //  // 文件无法打开
	ERR_FILE_MISSING_DEPENDENCIES, // 文件确实依赖
	ERR_FILE_EOF, // 文件结束
	ERR_CANT_OPEN, ///< 无法打开 resource/socket/file
	ERR_CANT_CREATE, // 无法创建
	ERR_QUERY_FAILED, // 请求失败
	ERR_ALREADY_IN_USE, // 在使用中
	ERR_LOCKED, // 资源被上锁
	ERR_TIMEOUT, // 超时
	ERR_CANT_CONNECT, // 无法连接
	ERR_CANT_RESOLVE, // 无法解决
	ERR_CONNECTION_ERROR, // 连接错误
	ERR_CANT_ACQUIRE_RESOURCE, // 无法获得资源
	ERR_CANT_FORK, // 无法分叉
	ERR_INVALID_DATA, // 传递的数据无效
	ERR_INVALID_PARAMETER, // 传递的参数无效
	ERR_ALREADY_EXISTS, // 已经存在
	ERR_DOES_NOT_EXIST, // 不存在
	ERR_DATABASE_CANT_READ, // 数据库已满
	ERR_DATABASE_CANT_WRITE, // 数据库已满
	ERR_COMPILATION_FAILED, // 编译失败
	ERR_METHOD_NOT_FOUND, // 方法未找到
	ERR_LINK_FAILED, // 链接失败
	ERR_SCRIPT_FAILED, // 脚本
	ERR_CYCLIC_LINK, // 循环链接
	ERR_INVALID_DECLARATION, // 无效的声明
	ERR_DUPLICATE_SYMBOL, // 符号重复
	ERR_PARSE_ERROR, // 解析错误
	ERR_BUSY, // 忙
	ERR_SKIP, // 跳过
	ERR_HELP, // 用户请求帮助
	ERR_BUG, ///< a bug in the software certainly happened, due to a double check failing or unexpected behavior.
	ERR_PRINTER_ON_FIRE, /// the parallel port printer is engulfed in flames
	ERR_MAX, // 错误数量
};

const char *error_names[] = {
	"OK", // OK
	"Failed", // FAILED
	"Unavailable", // ERR_UNAVAILABLE
	"Unconfigured", // ERR_UNCONFIGURED
	"Unauthorized", // ERR_UNAUTHORIZED
	"Parameter out of range", // ERR_PARAMETER_RANGE_ERROR
	"Out of memory", // ERR_OUT_OF_MEMORY
	"File not found", // ERR_FILE_NOT_FOUND
	"File: Bad drive", // ERR_FILE_BAD_DRIVE
	"File: Bad path", // ERR_FILE_BAD_PATH
	"File: Permission denied", // ERR_FILE_NO_PERMISSION
	"File already in use", // ERR_FILE_ALREADY_IN_USE
	"Can't open file", // ERR_FILE_CANT_OPEN
	"Can't write file", // ERR_FILE_CANT_WRITE
	"Can't read file", // ERR_FILE_CANT_READ
	"File unrecognized", // ERR_FILE_UNRECOGNIZED
	"File corrupt", // ERR_FILE_CORRUPT
	"Missing dependencies for file", // ERR_FILE_MISSING_DEPENDENCIES
	"End of file", // ERR_FILE_EOF
	"Can't open", // ERR_CANT_OPEN
	"Can't create", // ERR_CANT_CREATE
	"Query failed", // ERR_QUERY_FAILED
	"Already in use", // ERR_ALREADY_IN_USE
	"Locked", // ERR_LOCKED
	"Timeout", // ERR_TIMEOUT
	"Can't connect", // ERR_CANT_CONNECT
	"Can't resolve", // ERR_CANT_RESOLVE
	"Connection error", // ERR_CONNECTION_ERROR
	"Can't acquire resource", // ERR_CANT_ACQUIRE_RESOURCE
	"Can't fork", // ERR_CANT_FORK
	"Invalid data", // ERR_INVALID_DATA
	"Invalid parameter", // ERR_INVALID_PARAMETER
	"Already exists", // ERR_ALREADY_EXISTS
	"Does not exist", // ERR_DOES_NOT_EXIST
	"Can't read database", // ERR_DATABASE_CANT_READ
	"Can't write database", // ERR_DATABASE_CANT_WRITE
	"Compilation failed", // ERR_COMPILATION_FAILED
	"Method not found", // ERR_METHOD_NOT_FOUND
	"Link failed", // ERR_LINK_FAILED
	"Script failed", // ERR_SCRIPT_FAILED
	"Cyclic link detected", // ERR_CYCLIC_LINK
	"Invalid declaration", // ERR_INVALID_DECLARATION
	"Duplicate symbol", // ERR_DUPLICATE_SYMBOL
	"Parse error", // ERR_PARSE_ERROR
	"Busy", // ERR_BUSY
	"Skip", // ERR_SKIP
	"Help", // ERR_HELP
	"Bug", // ERR_BUG
	"Printer on fire", // ERR_PRINTER_ON_FIRE
};

static_assert(sizeof(error_names) / sizeof(*error_names) == ERR_MAX);
