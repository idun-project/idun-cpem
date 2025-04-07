pkgname=idun-cpem
pkgver=1.2_beta
pkgrel=1
pkgdesc="CP/M integration for Idun"
arch=("armv7h")
url="https://github.com/idun-project/idun-cpem"
depends=(idun idun-base)
source=(cpem)
provides=(idun-cpem)
install="cpem.install"

build() {
	make CROSS=1
}

package() {
	install -D -m 755 ../build/cpem "${pkgdir}"/home/idun/idun-base/cpm/cpem
	find ../build -type f -exec install -Dm 644 "{}" "${pkgdir}/home/idun/idun-base/cpm/{}" \;
}
