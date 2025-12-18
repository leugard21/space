pkgname=space
pkgver=0.1.0
pkgrel=1
pkgdesc="Disk Usage Visual Analyzer"
arch=('x86_64')
url="https://leugard21.com/space"
license=('MIT')
depends=('glibc')
makedepends=('cmake' 'gcc' 'make')
provides=('space')
conflicts=('space-bin')
source=()
md5sums=()

build() {
  cmake -S "$startdir" -B "$srcdir/build" \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/usr
  cmake --build "$srcdir/build" -j"$(nproc)"
}

package() {
  DESTDIR="$pkgdir" cmake --install "$srcdir/build"
}
