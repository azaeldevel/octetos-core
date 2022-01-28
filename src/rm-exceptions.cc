

#include "shell.hh"

namespace oct::core
{


class UnmanageObjectException : public InternalException
{
protected:
	
public:
    UnmanageObjectException(const char* fn,int l) : InternalException(-1,fn,l)
    {    
    }
    UnmanageObjectException()
    {    
    }

	//functions
    virtual const char* what () const throw ()
    {
		return "Se desconoce el objeto que intene eliminar";
    }
};


class RemoveException : public InternalException
{
protected:
	
public:
    RemoveException(int c,const char* fn,int l) : InternalException(c,fn,l)
    {    
    }
    RemoveException(int c) : InternalException(c)
    {
    }

	//functions
    virtual const char* what () const throw ()
    {
		switch(code)
		{
					case EACCES:
						return "Write access to the directory containing pathname was not allowed, or one of the directories in the path prefix of pathname did not allow search permission";
						break;
					case EBUSY:
						return "pathname is currently in use by the system or some process that prevents its removal. On Linux this means pathname is currently used as a mount point or is the root directory of the calling process.";
						break;
					case EFAULT:
						return "pathname points outside your accessible address space";
						break;
					case EINVAL:
						return "pathname has . as last component";
						break;
					case ELOOP:
						return "Too many symbolic links were encountered in resolving pathname";
						break;
					case ENAMETOOLONG:
						return"pathname was too long";
						break;
					case ENOENT:
						return "A directory component in pathname does not exist or is a dangling symbolic link";
						break;
					case ENOMEM:
						return "Insufficient kernel memory was available";
						break;
					case ENOTDIR:
						return "pathname, or a component used as a directory in pathname, is not, in fact, a directory";
						break;
					case ENOTEMPTY:
						return "pathname contains entries other than . and .. ; or, pathname has .. as its final component. POSIX.1-2001 also allows EEXIST for this condition";
						break;
					case EPERM:
						return "The directory containing pathname has the sticky bit (S_ISVTX) set and the process's effective user ID is neither the user ID of the file to be deleted nor that of the directory containing it, and the process is not privileged (Linux: does not have the CAP_FOWNER capability)";
						break;
					case EROFS:
						return "pathname refers to a directory on a read-only file system";
						break;
		}
		return "Unknow error code.";
    }
};


class RemoveDirException : public InternalException
{
protected:
	
public:
    RemoveDirException(int c,const char* fn,int l) : InternalException(c,fn,l)
    {
    
    }
    RemoveDirException(int c) : InternalException(c)
    {    
    }

	//functions
    virtual const char* what () const throw ()
    {
		switch(code)
		{
					case EACCES:
						return "Write access to the directory containing pathname was not allowed, or one of the directories in the path prefix of pathname did not allow search permission";
						break;
					case EBUSY:
						return "pathname is currently in use by the system or some process that prevents its removal. On Linux this means pathname is currently used as a mount point or is the root directory of the calling process.";
						break;
					case EFAULT:
						return "pathname points outside your accessible address space";
						break;
					case EINVAL:
						return "pathname has . as last component";
						break;
					case ELOOP:
						return "Too many symbolic links were encountered in resolving pathname";
						break;
					case ENAMETOOLONG:
						return "pathname was too long";
						break;
					case ENOENT:
						return "A directory component in pathname does not exist or is a dangling symbolic link";
						break;
					case ENOMEM:
						return "Insufficient kernel memory was available";
						break;
					case ENOTDIR:
						return "pathname, or a component used as a directory in pathname, is not, in fact, a directory";
						break;
					case ENOTEMPTY:
						return "pathname contains entries other than . and .. ; or, pathname has .. as its final component. POSIX.1-2001 also allows EEXIST for this condition";
						break;
					case EPERM:
						return "The directory containing pathname has the sticky bit (S_ISVTX) set and the process's effective user ID is neither the user ID of the file to be deleted nor that of the directory containing it, and the process is not privileged (Linux: does not have the CAP_FOWNER capability)";
						break;
					case EROFS:
						return "pathname refers to a directory on a read-only file system";
						break;
		}
		
		return "Unknow error code.";
    }
};

class UnlinkException : public InternalException
{
protected:
    int line,code;
    const char* filename;
	
public:
    UnlinkException(int c,const char* fn,int l) : InternalException(c,fn,l)
    {    
    }
    UnlinkException(int c) : code(c)
    {    
    }

	//functions
    virtual const char* what () const throw ()
    {
		switch(code)
		{
					case EACCES:
						return "Write access to the directory containing pathname is not allowed for the process's effective UID, or one of the directories in pathname did not allow search permission";
						break;
					case EBUSY:
						return "The file pathname cannot be unlinked because it is being used by the system or another process; for example, it is a mount point or the NFS client software created it to represent an active but otherwise nameless inode (\"NFS silly renamed\")";
						break;
					case EFAULT:
						return "pathname points outside your accessible address space";
						break;
					case EIO:
						return "An I/O error occurred";
						break;
					case EISDIR:
						return "pathname refers to a directory";
						break;
					case ELOOP:
						return "Too many symbolic links were encountered in translating pathname";
						break;
					case ENAMETOOLONG:
						return "pathname was too long";
						break;
					case ENOENT:
						return "A component in pathname does not exist or is a dangling symbolic link, or pathname is empty.";
						break;
					case ENOMEM:
						return "Insufficient kernel memory was available";
						break;
					case ENOTDIR:
						return "A component used as a directory in pathname is not, in fact, a directory";
						break;
					case EPERM:
						return "The system does not allow unlinking of directories, or unlinking of directories requires privileges that the calling process doesn't have";
						break;
					case EROFS:
						return "pathname refers to a file on a read-only file system";
						break;
		}
		return "Unknow error code.";
    }
};


}