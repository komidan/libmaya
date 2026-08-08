# CHANGELOG

This project (attempts) to follow:
- [Keep a Changelog](https://keepachangelog.com/en/1.1.0/)
- [Semantic Versioning](https://semver.org/)

_Dates are formatted DD-MM-YYYY_

- - -

## [Unreleased]
- None at the moment!

- - -

## [0.2.0] - 7.8.2026

## Added
- `MAYA_COMPILER` string define
- Terminal Control Sequences (check `MAYA_MODULE_ANSI`)
- A whole bunch of doxygen styled documentation. `libmaya.h` should be used as a documentation source.

## Fixes
- C Version Check was wrong; `< MAYA_C89` -> `< MAYA_C90`
- MSVC compiler check was wrong; `_MSC_VER_` -> `_MSC_VER`
- Removed trailing semicolons on `TODO` and `LOG` defines

## Changed
- Moved `MAYA_MODULE_COLORS` definitions into `MAYA_MODULE_ANSI` for consistency.
- Renamed define `MAYA_PLATFORM` to `MAYA_OS` for consistency.
- Renamed some definitions from `MAYA_*` to their expected name. (e.g `ANSI_*` or `COLOR_*`) including writing out `COLOR_BRIGHT_RED` or `COLOR_RED` over the old naming.
- Unknown os/platform now defines `MAYA_OS` as `UNKNOWN`
- Unknown compiler now defines `MAYA_COMPILER` as `UNKNOWN`
- Typos and wrong `defined()` checks
- Moved `TODO` to module `MAYA_MODULE_ANSI`.

- - -

## [0.1.1] - 30.7.2026

### Fixes
- Typos and fixes

### Removed
- CPP Extern statement; will be readded if needed (and works) later.

- - -

## [0.1.0] - 29.7.2026

### Added
- Basic Module Implementations (ANSI, TYPES, BITS)
