const Actions = {
    setSources: 'setSources', // payload: { sources : [ Source ] },
    updateSources: 'updateSources', // payload: <same as MQ event for topics.nmos.sender_list_update>,
    deleteLiveSources: 'deleteLiveSources', // payload: { ids : [ String ] },

    // payload: {
    //      ids : [ String ] },
    //      filename : [ String ] },
    //      durationMs : [ String ] },
    captureFromSources: 'captureFromSources',

    showAddSource: 'showAddSource',
    hideAddSource: 'hideAddSource',
    addSources: 'addSources', // payload: { sources: [ { dstAddr, dstPort } ] },
    showEditSource: 'showEditSource',
    hideEditSource: 'hideEditSource',
    showSDPErrorPopUp: 'showSDPErrorPopUp', // payload: { id },
    hideSDPErrorPopUp: 'hideSDPErrorPopUp',
};

export default Actions;