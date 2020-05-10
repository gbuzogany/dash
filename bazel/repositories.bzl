load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def dash_repositories():

    _maybe(
        http_archive,
        name = "net_zlib_zlib",
        sha256 = "6d4d6640ca3121620995ee255945161821218752b551a1a180f4215f7d124d45",
        build_file = "@com_gbuzogany_dash//bazel/third_party:zlib.BUILD",
        strip_prefix = "zlib-cacf7f1d4e3d44d871b605da3b647f07d718623f",
        urls = [
            "https://github.com/madler/zlib/archive/cacf7f1d4e3d44d871b605da3b647f07d718623f.tar.gz"
        ]
    )

    _maybe(
        http_archive,
        name = "glm",
        sha256 = "6b79c3d06d9745d1cce3f38c0c15666596f9aefff25ddb74df3af0a02f011ee1",
        build_file = "@com_gbuzogany_dash//bazel/third_party:glm.BUILD",
        strip_prefix = "glm",
        urls = [
            "https://github.com/g-truc/glm/releases/download/0.9.9.7/glm-0.9.9.7.zip"
        ]
    )

    _maybe(
        http_archive,
        name = "org_freetype_freetype2",
        build_file = "@com_gbuzogany_dash//bazel/third_party:freetype2.BUILD",
        sha256 = "33a28fabac471891d0523033e99c0005b95e5618dc8ffa7fa47f9dadcacb1c9b",
        strip_prefix = "freetype-2.8",
        urls = [
            "http://download.savannah.gnu.org/releases/freetype/freetype-2.8.tar.gz"
        ]
    )

    _maybe(
        http_archive,
        name = "org_libpng_libpng",
        build_file = "@com_gbuzogany_dash//bazel/third_party:libpng.BUILD",
        sha256 = "7f415186d38ca71c23058386d7cf5135c8beda821ee1beecdc2a7a26c0356615",
        strip_prefix = "libpng-1.2.57",
        urls = [
            "https://github.com/glennrp/libpng/archive/v1.2.57.tar.gz"
        ]
    )

    _maybe(
        http_archive,
        name = "com_github_grpc_grpc",
        sha256 = "4cbce7f708917b6e58b631c24c59fe720acc8fef5f959df9a58cdf9558d0a79b",
        strip_prefix = "grpc-1.28.1",
        urls = [
            "https://github.com/grpc/grpc/archive/v1.28.1.tar.gz"
        ]
    )

    _maybe(
        http_archive,
        name = "rules_python",
        sha256 = "e5470e92a18aa51830db99a4d9c492cc613761d5bdb7131c04bd92b9834380f6",
        strip_prefix = "rules_python-4b84ad270387a7c439ebdccfd530e2339601ef27",
        urls = [
            "https://github.com/bazelbuild/rules_python/archive/4b84ad270387a7c439ebdccfd530e2339601ef27.tar.gz"
        ]
    )

    _maybe(
        http_archive,
        name = "sdl2",
        sha256 = "64c3c997747e8c80e3e36fea12e2222e8a6fca7b348bdfdbaafd1ceb9fe80ba7",
        strip_prefix = "sdl2-0.1",
        urls = [
            "https://github.com/gbuzogany/sdl2/archive/v0.1.tar.gz"
        ]
    )

def _maybe(repo_rule, name, **kwargs):
    if name not in native.existing_rules():
        repo_rule(name = name, **kwargs)