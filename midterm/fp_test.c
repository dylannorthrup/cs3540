#include "football_player.h"

int main() {
  football_player* fp;
  fp = create_football_player("Jaquez Parks", "None Yet", 0);
  display_player(fp);
  additional_jerseys_signed(fp, 5);
  display_player(fp);
  delete_player(fp);

  return 0;
}
