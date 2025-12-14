#!/bin/bash
# Compile and copy to the dist directory

set -e

# Clean and rebuild
rm -rf build
meson setup build
ninja -C build

# Create output directory
mkdir -p dist/wm5/1.05.00
mkdir -p dist/w5p/3.05.00
mkdir -p dist/wm6/1.03.04
mkdir -p dist/w6r/2.00.08
mkdir -p dist/w6w/3.05.03

# Copy DLL
cp build/bngrw_wm5_10500.dll dist/wm5/1.05.00/bngrw.dll
cp build/bngrw_w5p_30500.dll dist/w5p/3.05.00/bngrw.dll
cp build/bngrw_wm6_10304.dll dist/wm6/1.03.04/bngrw.dll
cp build/bngrw_w6r_20008.dll dist/w6r/2.00.08/bngrw.dll
cp build/bngrw_w6w_30503.dll dist/w6w/3.05.03/bngrw.dll

echo "Build complete!"
echo "  dist/wm5/1.05.00/bngrw.dll"
echo "  dist/w5p/3.05.00/bngrw.dll"
echo "  dist/wm6/1.03.04/bngrw.dll"
echo "  dist/w6r/2.00.08/bngrw.dll"
echo "  dist/w6w/3.05.03/bngrw.dll"