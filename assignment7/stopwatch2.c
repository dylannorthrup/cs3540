#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <setjmp.h>

// Method declarations
static void sig_int (int signo);
static void sig_alarm (int signo);
static void sig_quit (int signo);
void err_sys (const char* message);

// Global variables
static jmp_buf alarm_jmp;
static int timer_enabled = 1;

int main (int argc, char* argv[]) {
  int secs_elapsed = 0;
  // Register signal handlers
  if (signal (SIGINT, sig_int) == SIG_ERR) {
    err_sys ("quit signal error");
  }
  if (signal (SIGQUIT, sig_quit) == SIG_ERR) {
    err_sys ("quit signal error");
  }
  if (signal (SIGALRM, sig_alarm) == SIG_ERR) {
    err_sys ("alarm signal error");
  }
  // Start the clock ticking with an alarm
  alarm (1);
  if (sigsetjmp (alarm_jmp, 1) != 0) {
    secs_elapsed++;
    // Boolean to determine if we actuall output stuff
    if(timer_enabled) {
      printf ("%d\n", secs_elapsed);
      alarm (1);
    }
  }
  while (1);
  exit(0);
}

// Pause and resume output on SIGINT (^C)
static void sig_int (int signo) {
  if(timer_enabled) {
    // Print out something to tell the user what's going on and how to restore output
    printf("\nTIMER DISABLED - Press ^C again to resume timer\n"); 
    alarm(0);
    timer_enabled = 0;
  } else {
    // Tell them things are back
    printf("\nTIMER ENABLED\n"); 
    alarm(1);
    timer_enabled = 1;
//    siglongjmp (alarm_jmp, 1);
  }
}

// Exit program on SIGQUIT (^\)    
static void sig_quit (int signo) {
  printf("\n"); // add a newline so the prompt isn't all funky
  exit(0);
}

// Used for timing via sigalarm
static void sig_alarm (int signo) {
  siglongjmp (alarm_jmp, 1);
}

void err_sys (const char* message) {
  printf ("%s\n", message);
  exit (0);
}
