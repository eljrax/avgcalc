# cd .. && cp -rf avg avgcalc-0.1 && tar -zcvf avgcalc-0.1.tar.gz avgcalc-0.1 && rm -rf avgcalc-0.1 && rpmbuild -ta avgcalc-0.1.tar.gz
Summary: avgcalc - generates statistical information on input of numbers
Name: avgcalc
Version: 0.1
Release: 1
License: GPL
Group: Applications/Statistics
Source: http://theon.synackfin.co.uk/~erik/avgcalc-0.1.tar.gz
URL: http://theon.synackfin.co.uk/~erik/
Vendor: Erik Ljungstrom
Packager: Erik Ljungstrom < erik[-at-]ibiblio[-dot-]org >

%description
Reads numbers from a file or stdin and spits out statistical
information such as standard deviation, variance, mode etc.

%prep
%setup -q

%configure


%build
%{__make}

%install
%{__rm} -rf %{buildroot}
%{__make} install  DESTDIR="%{buildroot}" AM_INSTALL_PROGRAM_FLAGS=""

%files
%defattr(-,root,root)
/usr/share/doc/avgcalc/README
/usr/share/doc/avgcalc/COPYING
/usr/share/doc/avgcalc/ChangeLog
/usr/bin/avgcalc
/usr/share/man/man1/avgcalc.1.gz
/usr/share/locale/sv_SE/LC_MESSAGES/avgcalc.mo
/usr/share/locale/pl/LC_MESSAGES/avgcalc.mo
