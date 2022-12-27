#include "src/userManagement.h"

int main()
{
    struct dataUser user[checkLines("database/account.txt")/45 + 1];
    readFile(user, checkLines("database/account.txt")/45);
    menu(user, 0, checkLines("database/account.txt")/45);

    return 0;
}
