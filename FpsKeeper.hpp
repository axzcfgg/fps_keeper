#ifndef FPSKEEPERH
#define FPSKEEPERH


// fps keeper
namespace fps {
	class keeper {
	private:
		unsigned long frame_time;
 		unsigned long prev_time;
		unsigned long bresenham_err;
		unsigned int fps;

		// sleep milliseconds
 		void sleep(const unsigned int m_sec);
	public:
		keeper();

		// set fps
		keeper(const unsigned int fps_);

		// calculate elapsed time, and set waiting time to keep fps
		// if this->sleep is called, then return true. if not, return false
 		bool wait();

		// change fps to keep:
		// if fps_ is zero, nothing will set by this function,
		// so you have to set fps_ greater than zero.
 		void set_fps(const unsigned int fps_);

	}; // end class
} // end namespace

#endif
