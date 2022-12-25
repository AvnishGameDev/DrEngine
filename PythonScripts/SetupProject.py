#!/usr/bin/env python3.1
print('Copyright Avnish Kirnalli 2022. Made for DrEngine.')

import os
import shutil
import subprocess
from io import BytesIO

# Module checks with Install option
def yes_or_no(question):
    reply = str(input(question + ' (y/n): ')).lower().strip()
    if reply[0] == 'y':
        return True
    if reply[0] == 'n':
        return False

def InstallModule(package):
    if yes_or_no(f'Package {package} not found. Do you want to install Python Package {package}?'):
        subprocess.call(['pip', 'install', package])
        os.system('cls')
        os.system(f'python {os.getcwd()}/PythonScripts/SetupProject.py')
        exit()
    else:
        exit()

try:
    import requests
except ImportError as e:
    InstallModule('requests')
try:
    import zipfile
except ImportError as e:
    InstallModule('zipfile')
try:
    from tqdm import tqdm
except ImportError as e:
    InstallModule('tqdm')
try:
    from colorama import Fore, Back, Style
except ImportError as e:
    InstallModule('colorama')

os.chdir(f'{os.getcwd()}/PythonScripts')

def DownloadSDL():
    response = requests.get("https://api.github.com/repos/libsdl-org/SDL/releases/latest")
    versionNo = response.json()["name"]

    if os.path.exists(f'{os.getcwd()}/../DrEngine/vendor/SDL2'):
        f = open(f'{os.getcwd()}/../DrEngine/vendor/SDL2/version.txt')
        if f.read() == versionNo:
            print(Fore.LIGHTBLUE_EX + 'SDL2 Up-to date')
            return
        else:
            print('SDL Outdated')
            print('Updating SDL2')

    print('Downloading SDL2')

    print(f"SDL Version: {versionNo}")

    url = f'https://github.com/libsdl-org/SDL/releases/download/release-{versionNo}/SDL2-devel-{versionNo}-VC.zip'
    req = requests.get(url)

    filename = url.split('/')[-1]

    with open(filename, 'wb') as output_file:
        output_file.write(req.content)

    print('Downloaded SDL2.')

    print('Starting SDL2 Extraction')

    with zipfile.ZipFile(BytesIO(req.content)) as zf:
        for member in tqdm(zf.infolist(), desc='Extracting SDL '):
            try:
                zf.extract(member, os.getcwd())
            except zipfile.error as e:
                print(f'Error while extracting SDL2: {e}')
                pass

    print('SDL2 extracted Successfully')

    print('Deleting SDL2 Residual Files')

    os.remove(f'{os.getcwd()}/{filename}')

    print('Finalizing SDL2 Setup')

    os.rename(f'SDL2-{versionNo}', 'SDL2')

    # writing version.txt
    with open('SDL2/version.txt', "w") as f:
        f.write(versionNo)

    shutil.move(f'{os.getcwd()}/SDL2', f'{os.getcwd()}/../DrEngine/vendor/SDL2')

    print(Fore.BLUE + 'SDL2 installed Successfully!')

def DownloadSPDLOG():
    response = requests.get("https://api.github.com/repos/gabime/spdlog/releases/latest")
    versionNo = response.json()["name"]
    versionNo = versionNo.replace('Version ', ' ').strip()

    if os.path.exists(f'{os.getcwd()}/../DrEngine/vendor/spdlog'):
        f = open(f'{os.getcwd()}/../DrEngine/vendor/spdlog/version.txt')
        if f.read() == versionNo:
            print(Fore.LIGHTBLUE_EX + 'SPDLOG Up-to date')
            return
        else:
            print('SPDLOG Outdated')
            print('Updating SPDLOG')

    print('Downloading SPDLOG.')

    print(f"SPDLOG Version: {versionNo}")

    url = f'https://github.com/gabime/spdlog/archive/refs/tags/v{versionNo}.zip'
    req = requests.get(url)

    filename = url.split('/')[-1]

    with open(filename, 'wb') as output_file:
        output_file.write(req.content)

    print('Downloaded SPDLOG.')

    print('Starting SPDLOG Extraction')

    with zipfile.ZipFile(BytesIO(req.content)) as zf:
        for member in tqdm(zf.infolist(), desc='Extracting SPDLOG '):
            try:
                zf.extract(member, os.getcwd())
            except zipfile.error as e:
                print(f'Error while extracting SPDLOG: {e}')
                pass

    print('SPDLOG extracted Successfully')

    print('Deleting SPDLOG Residual Files')

    os.remove(f'{os.getcwd()}/{filename}')

    print('Finalizing SPDLOG Setup')

    os.rename(f'spdlog-{versionNo}', 'spdlog')

    # writing version.txt
    with open('spdlog/version.txt', "w") as f:
        f.write(versionNo)

    shutil.move(f'{os.getcwd()}/spdlog', f'{os.getcwd()}/../DrEngine/vendor/spdlog')

    print(Fore.BLUE + 'SPDLOG installed successfully!')

def DownloadPremake():
    if os.path.exists(f'{os.getcwd()}/../vendor/bin/premake'):
        print(Fore.LIGHTBLUE_EX + 'Premake Up-to date')
        return

    print('Downloading Premake.')

    url = f'https://github.com/premake/premake-core/releases/download/v5.0.0-beta2/premake-5.0.0-beta2-windows.zip'
    req = requests.get(url)

    filename = url.split('/')[-1]


    with open(filename, 'wb') as output_file:
        output_file.write(req.content)

    print('Downloaded Premake.')

    print('Starting Premake Extraction')

    with zipfile.ZipFile(BytesIO(req.content)) as zf:
        zf.extract('premake5.exe', 'premake/')

    print('Premake extracted Successfully')

    print('Deleting Premake Residual Files')

    os.remove(f'{os.getcwd()}/{filename}')

    print('Downloading Premake License')

    url = f'https://raw.githubusercontent.com/premake/premake-core/master/LICENSE.txt'
    req = requests.get(url)

    with open('premake/LICENSE.txt', 'wb') as output_file:
        output_file.write(req.content)

    print('Premake License downloaded.')

    print('Finalizing Premake Setup')

    shutil.move('premake', '../vendor/bin/premake')

    print(Fore.BLUE + 'Premake installed successfully!')

DownloadPremake()
DownloadSPDLOG()
DownloadSDL()

print(Fore.GREEN + 'Setup Complete! Run GenerateProjectFiles.bat to generate Visual Studio 2022 Solution.')


