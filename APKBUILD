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
	install -D -m 755 "$builddir/cpem/cpem.bin" "${pkgdir}"/usr/local/bin/cpem.bin
	install -D -m 755 "$builddir/cpem.sh" "${pkgdir}"/usr/local/bin/cpem
}
