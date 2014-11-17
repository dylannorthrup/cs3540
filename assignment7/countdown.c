#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <setjmp.h>

static void sig_alarm (int signo);

void err_sys (const char* message);

static jmp_buf alarm_jmp;

int main (int argc, char* argv[])
{
  int time_left = 10;
  if (signal (SIGALRM, sig_alarm) == SIG_ERR)
    err_sys ("alarm signal error");
  alarm (1);
  if (sigsetjmp (alarm_jmp, 1) != 0)
  {
    time_left--;
    if (time_left == 0)
    {
      printf ("BOOM\n");
      exit(0);
    }
    else
    {
      printf ("%d\n", time_left);
      alarm (1);
    }
  }
  while (1);
  exit(0);
}

static void sig_alarm (int signo)
{
  siglongjmp (alarm_jmp, 1);
}

void err_sys (const char* message)
{
  printf ("%s\n", message);
  exit (0);
}
