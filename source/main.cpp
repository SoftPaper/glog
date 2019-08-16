#include <iostream>
#include <cstdlib>
#include <string>
#include <cstdio>
#include "glog/logging.h"


#define LOGDIR 			"./log"
#define DEBUGFILE 		"./debug.log"
#define MKDIR 			"mkdir -p " LOGDIR
#define PROGRAM 		"[GOLE]"

#define ILOG LOG(INFO)
#define WLOG LOG(WARNING)
#define ELOG LOG(ERROR)
#define FLOG LOG(FATAL)		//会使程序终止,慎用！


//将信息输出到单独的文件和 LOG(ERROR)
void SignalHandle(const char *data, int size)
{
    std::string str = std::string(data, size);
	
    std::cout << "***************************************" << std::endl;
    std::cout << str << std::endl;
    std::cout << "***************************************" << std::endl;
    
	/*
     * 也可以直接在这里发送邮件或短信通知，不过这个方法是被回调多次的（每次回调只输出
     * 一行错误信息，所以如上面的记录到文件，也需要>以追加模式方可），所以这里发邮件或
     * 短信不是很适合，不过倒是可以调用一个 SHELL 或 PYTHON 脚本，而此脚本会先 sleep 3秒
     * 左右，然后将错    误信息通过邮件或短信发送出去，这样就不需要监控脚本定时高频率执
     * 行，浪费效率了。
     */
}

int main(int argc,char* argv[]) 
{  
    system(MKDIR);
	google::InitGoogleLogging(PROGRAM);	//程序名字
    
	FLAGS_stderrthreshold = google::FATAL;	//设置级别高于 google::INFO 的日志同时输出到屏幕
	
    FLAGS_colorlogtostderr = true;	//设置输出到屏幕的日志显示相应颜色
	
    FLAGS_v = 3;
    
    FLAGS_log_dir = LOGDIR;	//也可使用系统环境变量GOOGLE_LOG_DIR控制log根目录
	
    FLAGS_logbufsecs = 0; //缓冲日志输出，默认为30秒，此处改为立即输出
    FLAGS_max_log_size = 10; //最大日志大小为 100MB
    FLAGS_stop_logging_if_full_disk = true; //当磁盘被写满时，停止日志输出
    FLAGS_logtostderr = false; //设置日志消息是否转到标准输出而不是日志文件
    google::InstallFailureSignalHandler(); //捕捉 core dumped
    google::InstallFailureWriter(&SignalHandle); //默认捕捉 SIGSEGV 信号信息输出会输出到 stderr，可以通过下面的方法自定义输出>方式：

	
	while(true)
	{
		ILOG << "Error message!";
		WLOG << "Error message!";
		ELOG << "Error message!";
        sleep(2);
	}

	google::ShutdownGoogleLogging();

	getchar();

	return 0;
} 