﻿#include "SpriteStudio6EdPrivatePCH.h"
#include "AssetTypeActions_SsProject.h"
#include "Ss6Project.h"
#include "SsProjectViewer.h"

#define LOCTEXT_NAMESPACE "AssetTypeActions"


UClass* FAssetTypeActions_SsProject::GetSupportedClass() const
{
	return USs6Project::StaticClass();
}

void FAssetTypeActions_SsProject::OpenAssetEditor( const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor )
{
	for(int i = 0; i < InObjects.Num(); ++i)
	{
		FSsProjectViewer::CreateEditor(EToolkitMode::Standalone, EditWithinLevelEditor, InObjects[i]);
	}
}

void FAssetTypeActions_SsProject::GetActions(const TArray<UObject*>& InObjects, FMenuBuilder& MenuBuilder)
{
	auto SsProjectImports = GetTypedWeakObjectPtrs<USs6Project>(InObjects);

	MenuBuilder.AddMenuEntry(
		LOCTEXT("SsProject_Reimport", "Reimport"),
		LOCTEXT("SsProject_ReimportTooltip", "reimport sspj."),
		FSlateIcon(),
		FUIAction(
		FExecuteAction::CreateSP(this, &FAssetTypeActions_SsProject::ExecuteReimport, SsProjectImports),
		FCanExecuteAction()
		)
	);
}

void FAssetTypeActions_SsProject::ExecuteReimport(TArray<TWeakObjectPtr<USs6Project>> Objects)
{
	for (auto ObjIt = Objects.CreateConstIterator(); ObjIt; ++ObjIt)
	{
		auto Object = (*ObjIt).Get();
		if (Object)
		{
			FReimportManager::Instance()->Reimport(Object, /*bAskForNewFileIfMissing=*/true);
		}
	}
}

#undef LOCTEXT_NAMESPACE
