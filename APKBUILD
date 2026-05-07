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
145cd0d8a54018af08e9db503ecd9bdb67a95522b7488fd841dc6017e773a6b4c693ad04fb765ca721a790a193df3f5209b46e1e431c53a80bd655c48da3381a  idun-cpem-1.2.1.tar.gz
"
