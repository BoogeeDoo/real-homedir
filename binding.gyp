{
    "targets": [
        {
            "target_name": "homedir",
            "sources": [
                "./src/entry.cpp",
                "./src/homedir.cpp"
            ],
            "include_dirs": [
                "<!(node -e \"require('nan')\")"
            ]
        }
    ]
}
