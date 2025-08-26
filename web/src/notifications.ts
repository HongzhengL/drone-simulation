import $ from "jquery";

const notifcationList = $("#notification-list")[0] as HTMLUListElement;

function notify(message: string) {
  let notif: HTMLLIElement = document.createElement("li");
  notif.innerText = message;
  notifcationList.insertBefore(notif, notifcationList.firstChild);
}

export { notify };
