#include "src/userManagement.h"

int main()
{
    int idxLogin;
    struct dataUser user[3];
    readFile(user);
    menu(user, idxLogin);

    return 0;
}
