#include <tcl.h>
#include <tclOO.h>
#include <tdbc.h>
//#include <libpq-fe.h>

#include <stdio.h>

/* Initialization script */

static const char initScript[] =
    "namespace eval ::tdbc::postgre {}\n"
    "tcl_findLibrary tdbcpostgre " PACKAGE_VERSION " " PACKAGE_VERSION
    " tdbcpostgre.tcl TDBCPOSTGRE_LIBRARY ::tdbc::postgre::Library";



/* Configuration options for Postgre connections */

/* Data types of configuration options */

enum OptType {
    TYPE_STRING,		/* Arbitrary character string */
};

/* Locations of the string options in the string array */
enum OptStringIndex {

};

/* Flags in the configuration table */

#define CONN_OPT_FLAG_MOD 0x1	/* Configuration value changable at runtime */
#define CONN_OPT_FLAG_ALIAS 0x2	/* Configuration option is an alias */

 /* Table of configuration options */

static const struct {
    const char * name;	/* Option name */
    enum OptType type;	/* Option data type */
    int info;		/* Option index or flag value */
    int flags;		/* Flags - modifiable; SSL related; is an alias */
    const char* query;	/* How to determine the option value? */
} ConnOptions [] = {
// must-be encoding, isolation, timeout, readonly
};




extern DLLEXPORT int
Tdbcpostgre_Init(
    Tcl_Interp* interp		/* Tcl interpreter */
) {
    if (Tcl_InitStubs(interp, TCL_VERSION, 0) == NULL) {
	return TCL_ERROR;
    }
    if (Tcl_OOInitStubs(interp) == NULL) {
	return TCL_ERROR;
    }
    if (Tdbc_InitStubs(interp) == NULL) {
	return TCL_ERROR;
    }

    /* Provide the current package */

    if (Tcl_PkgProvide(interp, "tdbc::postgre", PACKAGE_VERSION) == TCL_ERROR) {
	return TCL_ERROR;
    }

   /* 
     * Evaluate the initialization script to make the connection class 
     */

    if (Tcl_Eval(interp, initScript) != TCL_OK) {
	return TCL_ERROR;
    }



	return TCL_OK;
}

