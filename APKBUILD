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
14c6f2d3bb40ff32210e23e059d2924752c5c023b999fb9a11929813a2471d9063f12591cabefab715701f8d02a62fdcc5043511a6cec4f22dd782dd2258f6d7  idun-cpem-1.2.1.tar.gz
"
