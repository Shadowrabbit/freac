 /* BonkEnc Audio Encoder
  * Copyright (C) 2001-2009 Robert Kausch <robert.kausch@bonkenc.org>
  *
  * This program is free software; you can redistribute it and/or
  * modify it under the terms of the "GNU General Public License".
  *
  * THIS PACKAGE IS PROVIDED "AS IS" AND WITHOUT ANY EXPRESS OR
  * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
  * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE. */

#include <jobs/job_adddirectory.h>
#include <cddb/cddbremote.h>

#include <utilities.h>

#include <boca.h>

using namespace BoCA;
using namespace BoCA::AS;

BonkEnc::JobAddDirectory::JobAddDirectory(const String &iDirectory) : JobAddFiles(Array<String>())
{
	directory = iDirectory;
}

BonkEnc::JobAddDirectory::~JobAddDirectory()
{
}

Void BonkEnc::JobAddDirectory::AddDirectory(const Directory &directory)
{
	if (directory.Exists())
	{
		const Array<Directory>	&myDirectories = directory.GetDirectories();
		const Array<File>	&myFiles = directory.GetFiles();

		foreach (Directory directory, myDirectories) AddDirectory(directory);
		foreach (File file, myFiles) files.Add(file);
	}
}

Bool BonkEnc::JobAddDirectory::ReadyToRun()
{
	if (!BoCA::JobList::Get()->IsLocked())
	{
		BoCA::JobList::Get()->Lock();

		return True;
	}

	return False;
}

Error BonkEnc::JobAddDirectory::Perform()
{
	SetText("Preparing...");

	AddDirectory(directory);

	return JobAddFiles::Perform();
}
