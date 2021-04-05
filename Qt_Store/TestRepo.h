#pragma once
#include "Repository.h"
#include "CosProduse.h"

void testAllRepos();

void testAllRepo(RepoAbstract* repo);

void testAdd(RepoAbstract* repo);

void testUpdate(RepoAbstract* repo);

void testRemove(RepoAbstract* repo);

void testAdaugaCos(RepoAbstract* repo);

void testModificaCos(RepoAbstract* repo);

void testStergeCos(RepoAbstract* repo);

void testSavetoFile(RepoAbstract* repo);