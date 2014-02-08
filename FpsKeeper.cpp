#include "FpsKeeper.hpp"
#include <limits.h>


// Windows
#if defined(WIN_BUILD)
	#include <windows.h>
#endif

// Linux
#if defined(LINUX_BUILD)
	#include <unistd.h>
	#include <sys/time.h>
	typedef unsigned long DWORD;
#endif

class sec {
public:
	enum {
		U_SEC = 1000000 ,
		M_SEC = 1000
	};
};

// constructor
fps::keeper::keeper() :
	frame_time(1000) ,
	prev_time(0) ,
	bresenham_err(0) ,
	fps(60)
{	
}

// constructor
fps::keeper::keeper(const unsigned int fps_) :
	frame_time(1000) ,
	prev_time(0) ,
	bresenham_err(0) ,
	fps(fps_)
{	
}

//timeGetTime() on linux
#if defined (LINUX_BUILD)
	DWORD timeGetTime() {
		struct timeval t={0}; 
		gettimeofday( &t , 0 );
		return ( (t.tv_sec * sec::U_SEC) + t.tv_usec ) / sec::M_SEC;
	}
#endif

void fps::keeper::set_fps(const unsigned int fps_) {
	if(fps_ == 0) return;
	fps = fps_;
}

bool fps::keeper::wait() {
	DWORD nowTime = timeGetTime() * fps;
	if(prev_time > nowTime){
		nowTime += ULONG_MAX - prev_time;
		prev_time = 0;
	}
	DWORD processTime = nowTime - prev_time;	
	prev_time = nowTime;
	if(frame_time + bresenham_err > processTime){
		DWORD waitTime = frame_time + bresenham_err - processTime;
		bresenham_err = waitTime % fps;
		waitTime -= bresenham_err;
		fps::keeper::sleep(waitTime / fps);
		prev_time += waitTime;
		return true;
	}
	return false;
}


void fps::keeper::sleep(const unsigned int m_sec) {
	#if defined(WIN_BUILD)
		Sleep(m_sec);
	#elif defined(LINUX_BUILD)
		usleep( m_sec * sec::M_SEC );
	#endif
}

