
const buttonContainer = document.getElementById("buttonContainer")

const DetectedObjects = {

    createButtons(detectedObjects) {
        // Get the container where buttons will be added

        // Loop through the array
        for (var i = 0; i < detectedObjects.length; i++) {
            // Create a button element
            var button = document.createElement("button");

            // Set unique identifier for each button based on object type and index
            button.id = detectedObjects[i].object + "_button_" + i;

            // Set 'object' attribute as button text
            button.textContent = detectedObjects[i].object;

            // Create hidden input elements for 'x' and 'y'
            var hiddenX = document.createElement("input");
            hiddenX.type = "hidden";
            hiddenX.name = "x";
            hiddenX.value = detectedObjects[i].x;

            var hiddenY = document.createElement("input");
            hiddenY.type = "hidden";
            hiddenY.name = "y";
            hiddenY.value = detectedObjects[i].y;

            // Append hidden inputs to the button
            button.appendChild(hiddenX);
            button.appendChild(hiddenY);

            // Set a click event handler for the button
            button.addEventListener("click", function(event) {
                // Access 'x' and 'y' values based on the clicked button
                var clickedButtonId = event.target.id;
                var buttonIndex = clickedButtonId.split("_")[2];
                var clickedObject = detectedObjects[buttonIndex];

                // Do something with the 'x' and 'y' values of the clicked object
                console.log("Clicked Object:", clickedObject.object);
                console.log("Clicked Object X:", clickedObject.x);
                console.log("Clicked Object Y:", clickedObject.y);

                // Show selection in canvas
                UserCanvas.selectObject(clickedObject.x, clickedObject.y);
                // Disable button
                DetectedObjects.disableButton(event.target);
            });

            // Append the button to the container
            buttonContainer.appendChild(button);
        }
    },

    deleteButtons() {
        for (var i = buttonContainer.children.length - 1; i >= 0; i--) {
            var child = buttonContainer.children[i];

            // Check if the child element is a button
            if (child.tagName === 'BUTTON') {
                // Remove the button
                buttonContainer.removeChild(child);
            }
        }

        UserCanvas.unselectObject();
    },

    disableButton(button) {
        for (var i = buttonContainer.children.length - 1; i >= 0; i--) {
            var child = buttonContainer.children[i];

            // Check if the child element is a button
            if (child.tagName === 'BUTTON') {
                // Enable all buttons
                child.disabled = false;
            }
        }
        button.disabled = true;
    },
}
