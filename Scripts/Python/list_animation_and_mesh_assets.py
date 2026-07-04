import unreal


CLASSES = [
    "SkeletalMesh",
    "AnimMontage",
    "AnimSequence",
    "AnimationBlueprint",
]


def log(msg: str) -> None:
    unreal.log(f"[list_animation_and_mesh_assets] {msg}")


def main() -> None:
    registry = unreal.AssetRegistryHelpers.get_asset_registry()
    for class_name in CLASSES:
        log(f"class={class_name}")
        assets = registry.get_assets_by_class(unreal.TopLevelAssetPath(f"/Script/Engine.{class_name}"), True)
        for asset in assets:
            log(f"  {asset.package_name}")


if __name__ == "__main__":
    main()
