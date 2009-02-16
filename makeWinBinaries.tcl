#!/usr/bin/env tclsh8.6 $0 "$@"

set ver [package require tdbc]

set instdir [file normalize [file join  $::tcl_library ..]]
set pathlist tdbc${ver}
lappend pathlist {*}[glob -types d \
		  -directory $instdir \
		  -tails 1 \
		  {tdbc[a-z]*}]
lappend pathlist sqlite33.6.4
lappend pathlist tcl8/8.6/tdbc

set distdir /tmp/dist/tdbc${ver}-win32
file mkdir $distdir
set f [open [file join $distdir INSTALL.tcl] w]
puts $f {
    package require Tcl 8.6
    package require Tk
    grid [label .l -text "Installing TDBC drivers"]
    set distdir [file dirname [info script]]
    set instdir [file normalize [file join $::tcl_library ..]]
}

foreach dir $pathlist {
    file mkdir [file join $distdir $dir]
    puts $f "file mkdir \[file join \$instdir [list $dir]\]"
    foreach file [glob -directory [file join $instdir $dir] -tails *] {
	file copy -force [file join $instdir $dir $file] \
	    [file join $distdir $dir $file]
	puts $f "file copy -force \
                           \[file join \$distdir $dir $file\] \
                           \[file join \$instdir $dir $file\]"
    }
}
puts $f {
    tk_messageBox -type ok \
	-detail "Files installed in $instdir" \
	-message "TDBC drivers installed." \
	-icon info
    exit
}
close $f
exit
	