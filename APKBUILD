pkgname=idun-cpem
pkgver=1.2.1
pkgrel=1
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
ce786a1d06bccaea014621b41257bf66639a68ed20ce7de13f1ca172e88ae74089812d1d03ad4aa0f87b5dca3be893c0ad1d4054eff5a611551f149cb9c618c9  idun-cpem-1.2.1.tar.gz
"
