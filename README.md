# Welcome to the Tacview C# Add-ons Repository!

## Introduction

You will find here numerous samples and tools for Tacview. Feel free to experiment and modify the provided source codes.

## How to install an add-on?

The simplest way to install one of this addons is to download the whole repository in the folder of you choice.

Open the master solution called CS-AddOns.sln

Then build the addon of your choice.

This should generate the proper executable DLLs in sub folder(s) of:

```
%ProgramData%\Tacview\AddOns\
```

## How to develop my own add-on?

This repository is dedicated to C# add-ons. You need [Tacview Enterprise](https://www.tacview.net/features/enterprise/) to run C# addons.

The C# API is virtually identical the Lua one which is described in detail in:

```
%ProgramFiles(x86)%\Tacview\AddOns\Tacview Lua Core Interface.txt
%ProgramFiles(x86)%\Tacview\AddOns\Tacview Lua Main Interface.txt
```

If you want to publish your creation or changes, contact us at support@tacview.net and we will grant you access to this repository so you can share your own creation and improvements.

## Add-ons Catalogue

### Cartography

* [Maps Downloader](MapsDownloader) – Downloads and displays topographic and satellite maps from any WMS compliant server such as https://www.geoportail.gouv.fr/
