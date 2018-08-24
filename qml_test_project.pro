TEMPLATE = subdirs


#.subdir
#Use the specified subdirectory instead of SUBDIRS value.
#.file
#Specify the subproject pro file explicitly. Cannot be used in conjunction with .subdir modifier.
#.depends
#This subproject depends on specified subproject.
#.makefile
#The makefile of subproject. Available only on platforms that use makefiles.
#.target
#Base string used for makefile targets related to this subproject. Available only on platforms that use makefiles.

test_1.file = $$PWD/test_1/test_1.pro
test_0.file = $$PWD/test_0/test_0.pro

SUBDIRS += test_0
SUBDIRS += test_1



