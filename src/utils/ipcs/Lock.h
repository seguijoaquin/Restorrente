//
// Created by joaquin on 28/10/16.
//

#ifndef RESTORRENTE_LOCK_H
#define RESTORRENTE_LOCK_H


#include <unistd.h>
#include <fcntl.h>
#include <string.h>

class LockFile {

private:

	struct flock fl;
	int fd;
	char name [ 255 ];

public:

	LockFile ( const char* name );
	virtual ~LockFile();

	int tomarLock ();
	int liberarLock ();
	int escribir ( char* buffer,int buffsize );
};


#endif //RESTORRENTE_LOCK_H
