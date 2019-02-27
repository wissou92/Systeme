#include <sys/types.h>
#include <dirent.h>

int aff_contenu(const char* name)
{
	DIR* dfd = opendir(name);
	
	closedir(dfd);
}
