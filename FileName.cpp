#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <time.h>
#include <stdint.h>



struct Counter {
	intmax_t Value = 0;
	//clock_t Time = 0;//need elipse time is what counted?
};

void inc(Counter& c) {
	c.Value++;
	//c.Time = clock();
}

struct Timer {
	clock_t StartTime = 0;
	clock_t EndTime = 0;
	bool Running = false;
};
	void start(Timer& T) {
		T.StartTime = clock();
		T.Running = true;
	}
	void stop(Timer& T) {
		T.EndTime = clock();
		T.Running = false;
	}
	void reset(Timer& T) {
		T.StartTime = 0;
		T.EndTime = 0;
		T.Running = false;
	}
	void linner(Timer& T) {
		T.EndTime = clock();
	}
	clock_t elapsed(Timer& T){
		if(T.Running){
			return clock() - T.StartTime;
		}
		return T.EndTime - T.StartTime;
	}
	bool is_running(Timer& T){
		return T.Running;
	}

struct runner {
	char Tag[16] = "GAG BORAD!!";
	Counter C{};
	Timer T{};
	bool Running = false;
};

void start(runner& R) {
	R.Running = true;
	start(R.T);
}
void stop(runner& R) {
	R.Running = false;
	stop(R.T);
}
bool is_running(runner& R) {
	return R.Running;
}
void reset(runner& R) {
	R.Running = false;
	reset(R.T);
	R.C.Value = 0;
}
void reset_counter(runner& R) {
	R.C.Value = 0;
}
void reset_timer(runner& R) {
	reset(R.T);
}
void reset_all(runner& R) {
	reset(R);
}
void set_tag(runner& R, const char* tag) {
	strncpy(R.Tag, tag, sizeof(R.Tag) - 1);
	R.Tag[sizeof(R.Tag) - 1] = '\0';
}
void get_tag(runner& R, char* buffer, size_t size) {
	strncpy(buffer, R.Tag, size - 1);
	buffer[size - 1] = '\0';
}
void linner(runner& R) {
	linner(R.T);
}	

void inc(runner& R) {
	inc(R.C);
}
clock_t elapsed(runner& R) {
	return elapsed(R.T);
}
int main() {
	runner R;
	start(R);
	do{
		inc(R);
		linner(R);
	} while (elapsed(R) < CLOCKS_PER_SEC);//run for 1 second but CLOCKS_PER_SEC is platform dependent. maybe near 1000 is better this time only.
	std::cout << "Tag: " << R.Tag << "\n";
	std::cout << "Count: " << R.C.Value << "\n";
	std::cout << "Elapsed time (clock ticks): " << elapsed(R) << "\n";
	return 0;
}