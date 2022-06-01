#include <curses.h> // output
// FPS
#include <chrono>
#include <thread>
// Terminal size
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
// Signals
#include <csignal>

const int FPS = 5;
const float CYCLE_DURATION = 1000.0/FPS;

struct winsize w;
void update_size(int sig=0){
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w); // bind winsize variable
}

int main (int argc, char *argv[]){
  // for FPS
	auto start_cycle = std::chrono::system_clock::now();
	auto end_cycle = std::chrono::system_clock::now();
  // *******
  update_size(); // load size into w
  std::signal(SIGWINCH, update_size); // bind signal window change to function update_size
  initscr();   // init ncurses 
  curs_set(0); // cursor invisible
  noecho();    // input invisible

  while (true) {
		// for FPS 
		start_cycle = std::chrono::system_clock::now();
		std::chrono::duration<double, std::milli> work_time = start_cycle - end_cycle;

		if (work_time.count() < CYCLE_TIME){
			std::chrono::duration<double, std::milli> delta_ms(CYCLE_TIME - work_time.count());
			auto delta_ms_duration = std::chrono::duration_cast<std::chrono::milliseconds>(delta_ms);
			std::this_thread::sleep_for(std::chrono::milliseconds(delta_ms_duration.count()));
		}
		// *******

    // for FPS
		end_cycle = std::chrono::system_clock::now();
  }
  endwin();
  return 0;
}
