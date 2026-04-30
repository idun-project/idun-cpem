pkgname=idun-cpem
pkgver=1.2.1
pkgrel=0
pkgdesc="CP/M integration for Idun"
url="https://github.com/idun-project/idun-cpem"
arch="aarch64"
license="MIT"
depends="idun"
source="$pkgname-$pkgver.tar.gz"
builddir="$srcdir"
options="!check"
install="$pkgname.post-install $pkgname.post-deinstall"

build() {
	cd "$srcdir/cpem"
	make
}

package() {
	install -D -m 755 "$builddir/cpem/cpem.bin" "${pkgdir}"/usr/bin/cpem.bin
	install -D -m 755 "$builddir/cpem/cpem.sh" "${pkgdir}"/usr/bin/cpem
}
sha512sums="
de9b9808b49b7c9e9d39c476b9d57118e59816fb405ca5618adaadab1efe5e22de372b2ac4d7d120c71d4c7f6cdda3afd3a68ddba769c6477e0f9482bcd0701e  idun-cpem-1.2.1.tar.gz
"
