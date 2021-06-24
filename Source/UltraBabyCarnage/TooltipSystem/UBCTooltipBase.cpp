
#include "UBCTooltipBase.h"
#include "GameFramework/InputSettings.h"

FText UUBCTooltipBase::ParseText(const FText& message, bool useGamepadInputs) const
{
	const UInputSettings* inputSettings = GetDefault<UInputSettings>();
	TArray<FName> inputNames;
	inputSettings->GetActionNames(inputNames);

	FString messageString = message.ToString();
	for (int i = 0; i < messageString.Len(); i++)
	{
		if (messageString[i] == '<')
		{
			for (int j = i + 1; j < messageString.Len(); j++)
			{
				if (messageString[j] == '>')
				{
					FName inputName = FName(messageString.Mid(i + 1, j - i - 1));
					for (int k = 0; k < inputNames.Num(); k++)
					{
						TArray<FInputActionKeyMapping> bindings;
						inputSettings->GetActionMappingByName(inputName, bindings);

						if (bindings.Num() > 0)
						{
							for (int l = 0; l < bindings.Num(); l++)
							{
								bool isGamepad = bindings[l].Key.IsGamepadKey();
								if (useGamepadInputs && isGamepad || !useGamepadInputs && !isGamepad)
								{
									FString inputString = TEXT("img id=\"" + bindings[l].Key.ToString() + "\"></");
									messageString.RemoveAt(i + 1, j - i - 1);
									messageString.InsertAt(i + 1, inputString);
									
									i += inputString.Len();
									
									break;
								}
							}

							break;
						}
					}

					break;
				}
			}
		}
	}

	return FText::FromString(messageString);
}