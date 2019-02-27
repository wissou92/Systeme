#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int aff_type(const char* pathname)
{
	int retour;
	struct stat* sb;
	retour = stat(pathname, sb);
	 printf("Type de fichier :                ");

    switch (sb.st_mode & S_IFMT) {
    case S_IFBLK:  printf("périphérique de bloc\n");      break;
    case S_IFCHR:  printf("périphérique de caractère\n"); break;
    case S_IFDIR:  printf("répertoire\n");                break;
    case S_IFIFO:  printf("FIFO/tube\n");                 break;
    case S_IFLNK:  printf("lien symbolique\n");           break;
    case S_IFREG:  printf("fichier ordinaire\n");         break;
    case S_IFSOCK: printf("socket\n");                    break;
    default:       printf("inconnu ?\n");                 break;
    }
	return retour;	
}

int aff_permission(const char* pathname) {
	int retour;
	struct stat* sb;
	retour = stat(pathname, sb);
	printf("Permission du fichier :                ");

    switch (sb.st_mode & S_IRWXU) {
    case S_IRUSR: printf("r");            break;
    case S_IWUSR: printf("w");            break;
    case S_IXUSR: printf("x");            break;
    }
    printf(".");
    switch (sb.st_mode & S_IRWXG) {
    case S_IRGRP: printf("r");            break;
    case S_IWGRP: printf("w");            break;
    case S_IXGRP: printf("x");            break;
    }
    printf(".");
    switch (sb.st_mode & S_IRWXO) {
    case S_IROTH: printf("r");            break;
    case S_IWOTH: printf("w");            break;
    case S_IXOTH: printf("x");            break;
    }
    
	return retour;	
}

int aff_proprietaire(char const* pathname)
{
	int retour;
	struct stat* sb;
	retour = stat(pathname, sb);
	printf("Propriétaires :                    UID=%ld   GID=%ld\n",
            (long) sb.st_uid, (long) sb.st_gid);
    return retour;
}

int aff_taille(const char* pathname)
{
	int retour;
	struct stat* sb;
	retour = stat(pathname, sb);
	printf("Taille du fichier :                %lld octets\n",
            (long long) sb.st_size);
    return retour;
}
