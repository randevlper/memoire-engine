function NextButton()
	progressDialogue()
end

function MainMenuButton()
	loadWorld("assets/worlds/mainmenu")
end

function init()
-- Get text box and set that up for the dialogue writer
	setupWriter("Dialouge")
	startDialouge("assets/dialogue/test.dialogue")
end