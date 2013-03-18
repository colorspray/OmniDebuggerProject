all: check
		 @echo "------ODGame-----"
		 @echo "->Generate SWIG wrappers around the functions in the library"
		 "$(FLASCC)/usr/bin/swig" -c++ -as3 -module ODGameLib -outdir . -includeall -ignoremissing -o ODGameLib_wrapper.cpp swig.i

		 @echo "\n-> Compile the SWIG wrapper to ABC"
		 $(AS3COMPILERARGS) -abcfuture -AS3 -import $(call nativepath,$(FLASCC)/usr/lib/builtin.abc) -import $(call nativepath,$(FLASCC)/usr/lib/playerglobal.abc) ODGameLib.as

		 mv ODGameLib.as ODGameLib.as3

		 @echo "-> Compile the library into a SWC"
		 "$(FLASCC)/usr/bin/g++" $(BASE_CFLAGS) ODGameLib.abc ODGameLib_wrapper.cpp source/*.cpp -emit-swc=ODGame.ODGameLib -g -O0 -o ODGameLib.swc

include Makefile.common