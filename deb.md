<!-- SPDX-License-Identifier: zlib-acknowledgement -->
https://web.archive.org/web/20230329123130/https://www.boniface.me/debian-packaging-101/

simple to just create package on system you're on.
simple to not make any debian-specific changes to packages


debmake uses tarballs and directories with name permutations of name-version 
tarred-upstream folder alongside untarred-upstream folder
upstream means source before any changes by debian packagers

debian source package has info to create .deb binary package:
  - upstream tarball 
  - tarball of debian package information
  - .dsc checksum file

debmake creates generic debian/
but more specific ones for other languages, e.g npm2deb etc.
modify files generated from debmake
debian/
  - copyright
  - control: meta-data and dependencies
  - rules: build and install information
    debhelper commands, e.g:
    dh_auto_build etc. (mirrored after make clean etc.)

  - watch: $(uscan) rule to check for new upstream 
  - compat: debhelper version

  - changelog


dpkg-source creates source package

dpkg-buildpackage creates .deb

then import to a git repo with setup $(git branch/tag)

(debian salsa gitlab to host)
down to the road (ITP, sponsored package)
