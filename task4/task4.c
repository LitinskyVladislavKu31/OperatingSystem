#include <stdio.h>
#include <sys/types.h>
#include <pwd.h>

int main() {
    uid_t uid = geteuid(); // Отримуємо UID поточного користувача
    struct passwd *p = getpwuid(uid);

    if (p == NULL) {
        perror("getpwuid() error");
    } else {
        printf("getpwuid() returned the following info for uid %d:\n", (int) uid);
        printf("  pw_name  : %s\n", p->pw_name);
        printf("  pw_uid   : %d\n", (int) p->pw_uid);
        printf("  pw_gid   : %d\n", (int) p->pw_gid);
        printf("  pw_dir   : %s\n", p->pw_dir);
        printf("  pw_shell : %s\n", p->pw_shell);
    }

    char *username = "root";
    struct passwd *rootUserInfo = getpwnam(username); // Отримуємо інформацію про користувача за ім'ям

    if (rootUserInfo != NULL) {
        printf("\nІнформація про користувача '%s':\n", username);
        printf("Ім'я користувача: %s\n", rootUserInfo->pw_name);
        printf("Домашня директорія: %s\n", rootUserInfo->pw_dir);
        printf("UID користувача: %d\n", (int)rootUserInfo->pw_uid);
        printf("GID користувача: %d\n", (int)rootUserInfo->pw_gid);
    } else {
        printf("\nНе вдалося отримати інформацію про користувача '%s'.\n", username);
    }


    return 0;
}
