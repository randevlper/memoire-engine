function NextButton()
	progressDialogue()
end

function MainMenuButton()
	loadWorld("assets/worlds/mainmenu")
end

function init()
-- Get text box and set that up for the dialogue writer
	setupWriter("Dialogue", "Nameplate")
	dialogueAddSpriteRenderer("CharacterLeft")
	dialogueAddSpriteRenderer("CharacterRight")
	dialogueAddSpriteRenderer("CharacterLeft2")
	dialogueAddSpriteRenderer("CharacterRight2")
	startDialouge("assets/dialogue/test.dialogue")
end

function destroy()
	dialogueClear()
end