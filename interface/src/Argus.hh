#ifndef ARGUS_H
#define ARGUS_H

namespace argus
{

#ifndef WIN32
#	define ARGUS_EXPORT_DYNAMIC_LIBRARY
#   define ARGUS_IMPORT_DYNAMIC_LIBRARY
#else
#	define ARGUS_EXPORT_DYNAMIC_LIBRARY __declspec( dllexport )
#   define ARGUS_IMPORT_DYNAMIC_LIBRARY __declspec( dllimport )
#endif



#ifdef BUILD_ARGUS
#	define ARGUS_API ARGUS_EXPORT_DYNAMIC_LIBRARY
#else
#	define ARGUS_API ARGUS_IMPORT_DYNAMIC_LIBRARY
#endif


}


#endif // ARGUS_H