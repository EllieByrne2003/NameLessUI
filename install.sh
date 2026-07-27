#!/bin/bash

# Default installation prefix
PREFIX="${PREFIX:-/usr/local}"

# Library name and paths
LIB_NAME="libNLUI.so"
LIB_SOURCE="bin/${LIB_NAME}"
HEADER_SOURCE="include/"          # adjust if your headers are inside include/NameLessUtils/
HEADER_DEST="${PREFIX}/include/NLUI"

# Destination paths
LIB_DEST="${PREFIX}/lib"

# Check if the library binary exists
if [[ ! -f "$LIB_SOURCE" ]]; then
    echo "Error: $LIB_SOURCE not found. Please build the library first."
    exit 1
fi

# Create destination directories if they don't exist
mkdir -p "$LIB_DEST"
mkdir -p "$HEADER_DEST"

# Copy the shared library
echo "Installing $LIB_NAME to $LIB_DEST"
cp "$LIB_SOURCE" "$LIB_DEST/"
chmod 755 "$LIB_DEST/$LIB_NAME"

# Copy header files (preserve directory structure inside include/)
echo "Installing headers to $HEADER_DEST"
cd src
cp --parents **/*.hpp "$HEADER_DEST/"
# cp -r "$HEADER_SOURCE"* "$HEADER_DEST/"
cd ..

# Update the linker cache (optional, requires root)
if [[ "$EUID" -eq 0 ]]; then
    echo "Running ldconfig to update linker cache..."
    ldconfig
else
    echo "Skipping ldconfig (not root). You may need to run it manually."
fi

echo "Installation complete."