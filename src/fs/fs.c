#include "fs/fs.h"

#define _DEFAULT_SOURCE
#include <stddef.h>
#include <sys/stat.h>
#include <errno.h>
#include <dirent.h>

dir_t FsListDirStart(const char* path) {
	DIR* dir = opendir(path);
	return dir;
}

int FsListDir(dir_t dir, char** name, int* isDir) {
tryAgain:
	errno = 0;
	struct dirent* ent = readdir(dir);
	if (ent == NULL) {
		if (errno != 0) { // on error
			FsListDirEnd(dir);
			return 1;
		} else {
			*name = NULL;
			FsListDirEnd(dir);
		}
	} else if (ent->d_name[0] == '.') {
		goto tryAgain; // skip '.' && '..' entry
	} else {
		*name = ent->d_name;
		*isDir = ent->d_type == DT_DIR;
	}

	return 0;
}

void FsListDirEnd(dir_t dir) {
	if (dir) {
		closedir(dir);
	}
}

#include <string.h>

int fs_get_basename(const char* path) {
	int len = strlen(path);
	int index = 0;
	for (int i = 0; i < len; i++) {
		if (
			(path[i] == '/' || path[i] == '\\') &&
			i + 1 < len &&
			(path[i + 1] != '/' && path[i + 1] != '\\')
		) {
			index = i + 1;
		}
	}
	return index;
}