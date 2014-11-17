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
static int printing_enabled = 1;

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
    if (secs_elapsed == 0) {
      printf ("BOOM\n");
      exit(0);
    } else {
      if(printing_enabled) {
        printf ("%d\n", secs_elapsed);
      }
      alarm (1);
    }
  }
  while (1);
  exit(0);
}

static void sig_int (int signo) {
  if(printing_enabled) {
    printf("\nPRINTING DISABLED - Press ^C again to resume printing\n"); // add a newline so the prompt isn't all funky
    printing_enabled = 0;
  } else {
    printf("\nPRINTING ENABLED\n"); // add a newline so the prompt isn't all funky
    printing_enabled = 1;
  }
}

static void sig_quit (int signo) {
  printf("\n"); // add a newline so the prompt isn't all funky
  exit(0);
}

static void sig_alarm (int signo) {
  siglongjmp (alarm_jmp, 1);
}

void err_sys (const char* message) {
  printf ("%s\n", message);
  exit (0);
}
