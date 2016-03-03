{
    "targets": [
        {
            "target_name": "homedir",
            "sources": [
                "./src/entry.cpp",
                "./src/homedir.cpp",
                "./src/win_helper.cpp"
            ],
            "include_dirs": [
                "<!(node -e \"require('nan')\")"
            ],
            'conditions': [
                [ 'OS=="win"', {
                    'defines': [
                        '_WIN32_WINNT=0x0600',
                        '_GNU_SOURCE',
                    ],
                    'link_settings': {
                        'libraries': [
                            '-ladvapi32',
                            '-liphlpapi',
                            '-lpsapi',
                            '-lshell32',
                            '-luserenv',
                            '-lws2_32'
                        ],
                    }
                }]
            ]
        }
    ]
}