pkgname=idun-cpem
pkgver=1.2_beta
pkgrel=1
pkgdesc="CP/M integration for Idun"
arch=("armv7h")
url="https://github.com/idun-project/idun-cpem"
depends=(idun idun-base)
source=()
provides=(idun-cpem)
install="cpem.install"

build() {
	cd "${startdir}/cpem"
	make clean && make CROSS=1
}

package() {
	cd "${startdir}/cpem"
	install -D -m 755 cpem.sh "${pkgdir}"/usr/local/bin/cpem.sh
	install -d "${pkgdir}"/home/idun/idun-base/cpm
	make DESTDIR="${pkgdir}/home/idun" install
}
