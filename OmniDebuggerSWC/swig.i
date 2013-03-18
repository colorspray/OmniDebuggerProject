#ifdef SWIG
%module ODGameLibModule

%{
#include <stdlib.h>
#include <vector>
#include "source/ODGame.h"
#include "source/ODGameData.h"
%}

%include "source/ODGame.h"
%include "source/ODGameData.h"

#else
#include <stdlib.h>
#include <vector>
#include "source/ODGame.h"
#include "source/ODGameData.h"

#endif

